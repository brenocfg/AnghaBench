#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
struct TYPE_48__ {int /*<<< orphan*/  string; int /*<<< orphan*/  worth; } ;
struct TYPE_47__ {int /*<<< orphan*/ * initial_rels; } ;
struct TYPE_46__ {int /*<<< orphan*/ * join_search_private; } ;
struct TYPE_45__ {int /*<<< orphan*/  string_length; TYPE_1__* data; } ;
struct TYPE_44__ {scalar_t__ string; int /*<<< orphan*/  worth; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ Pool ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ GeqoPrivateData ;
typedef  int /*<<< orphan*/  Gene ;
typedef  int /*<<< orphan*/  Edge ;
typedef  int /*<<< orphan*/  City ;
typedef  TYPE_5__ Chromosome ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Geqo_seed ; 
 int /*<<< orphan*/  Geqo_selection_bias ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_5__* alloc_chromo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_city_table (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_edge_table (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* alloc_pool (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  best_plan ; 
 int cx (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_chromo (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  free_city_table (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_edge_table (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pool (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  geqo_eval (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geqo_mutation (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geqo_selection (TYPE_3__*,TYPE_5__*,TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geqo_set_seed (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimme_edge_table (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gimme_number_generations (int) ; 
 int gimme_pool_size (int) ; 
 scalar_t__ gimme_tour (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gimme_tree (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ox1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ox2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmx (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_gen (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  print_plan (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  print_pool (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  px (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_init_pool (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sort_pool (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  spread_chromo (TYPE_3__*,TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stdout ; 

RelOptInfo *
geqo(PlannerInfo *root, int number_of_rels, List *initial_rels)
{
	GeqoPrivateData private;
	int			generation;
	Chromosome *momma;
	Chromosome *daddy;
	Chromosome *kid;
	Pool	   *pool;
	int			pool_size,
				number_generations;

#ifdef GEQO_DEBUG
	int			status_interval;
#endif
	Gene	   *best_tour;
	RelOptInfo *best_rel;

#if defined(ERX)
	Edge	   *edge_table;		/* list of edges */
	int			edge_failures = 0;
#endif
#if defined(CX) || defined(PX) || defined(OX1) || defined(OX2)
	City	   *city_table;		/* list of cities */
#endif
#if defined(CX)
	int			cycle_diffs = 0;
	int			mutations = 0;
#endif

/* set up private information */
	root->join_search_private = (void *) &private;
	private.initial_rels = initial_rels;

/* initialize private number generator */
	geqo_set_seed(root, Geqo_seed);

/* set GA parameters */
	pool_size = gimme_pool_size(number_of_rels);
	number_generations = gimme_number_generations(pool_size);
#ifdef GEQO_DEBUG
	status_interval = 10;
#endif

/* allocate genetic pool memory */
	pool = alloc_pool(root, pool_size, number_of_rels);

/* random initialization of the pool */
	random_init_pool(root, pool);

/* sort the pool according to cheapest path as fitness */
	sort_pool(root, pool);		/* we have to do it only one time, since all
								 * kids replace the worst individuals in
								 * future (-> geqo_pool.c:spread_chromo ) */

#ifdef GEQO_DEBUG
	elog(DEBUG1, "GEQO selected %d pool entries, best %.2f, worst %.2f",
		 pool_size,
		 pool->data[0].worth,
		 pool->data[pool_size - 1].worth);
#endif

/* allocate chromosome momma and daddy memory */
	momma = alloc_chromo(root, pool->string_length);
	daddy = alloc_chromo(root, pool->string_length);

#if defined (ERX)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using edge recombination crossover [ERX]");
#endif
/* allocate edge table memory */
	edge_table = alloc_edge_table(root, pool->string_length);
#elif defined(PMX)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using partially matched crossover [PMX]");
#endif
/* allocate chromosome kid memory */
	kid = alloc_chromo(root, pool->string_length);
#elif defined(CX)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using cycle crossover [CX]");
#endif
/* allocate city table memory */
	kid = alloc_chromo(root, pool->string_length);
	city_table = alloc_city_table(root, pool->string_length);
#elif defined(PX)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using position crossover [PX]");
#endif
/* allocate city table memory */
	kid = alloc_chromo(root, pool->string_length);
	city_table = alloc_city_table(root, pool->string_length);
#elif defined(OX1)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using order crossover [OX1]");
#endif
/* allocate city table memory */
	kid = alloc_chromo(root, pool->string_length);
	city_table = alloc_city_table(root, pool->string_length);
#elif defined(OX2)
#ifdef GEQO_DEBUG
	elog(DEBUG2, "using order crossover [OX2]");
#endif
/* allocate city table memory */
	kid = alloc_chromo(root, pool->string_length);
	city_table = alloc_city_table(root, pool->string_length);
#endif


/* my pain main part: */
/* iterative optimization */

	for (generation = 0; generation < number_generations; generation++)
	{
		/* SELECTION: using linear bias function */
		geqo_selection(root, momma, daddy, pool, Geqo_selection_bias);

#if defined (ERX)
		/* EDGE RECOMBINATION CROSSOVER */
		gimme_edge_table(root, momma->string, daddy->string, pool->string_length, edge_table);

		kid = momma;

		/* are there any edge failures ? */
		edge_failures += gimme_tour(root, edge_table, kid->string, pool->string_length);
#elif defined(PMX)
		/* PARTIALLY MATCHED CROSSOVER */
		pmx(root, momma->string, daddy->string, kid->string, pool->string_length);
#elif defined(CX)
		/* CYCLE CROSSOVER */
		cycle_diffs = cx(root, momma->string, daddy->string, kid->string, pool->string_length, city_table);
		/* mutate the child */
		if (cycle_diffs == 0)
		{
			mutations++;
			geqo_mutation(root, kid->string, pool->string_length);
		}
#elif defined(PX)
		/* POSITION CROSSOVER */
		px(root, momma->string, daddy->string, kid->string, pool->string_length, city_table);
#elif defined(OX1)
		/* ORDER CROSSOVER */
		ox1(root, momma->string, daddy->string, kid->string, pool->string_length, city_table);
#elif defined(OX2)
		/* ORDER CROSSOVER */
		ox2(root, momma->string, daddy->string, kid->string, pool->string_length, city_table);
#endif


		/* EVALUATE FITNESS */
		kid->worth = geqo_eval(root, kid->string, pool->string_length);

		/* push the kid into the wilderness of life according to its worth */
		spread_chromo(root, kid, pool);


#ifdef GEQO_DEBUG
		if (status_interval && !(generation % status_interval))
			print_gen(stdout, pool, generation);
#endif

	}


#if defined(ERX) && defined(GEQO_DEBUG)
	if (edge_failures != 0)
		elog(LOG, "[GEQO] failures: %d, average: %d",
			 edge_failures, (int) number_generations / edge_failures);
	else
		elog(LOG, "[GEQO] no edge failures detected");
#endif

#if defined(CX) && defined(GEQO_DEBUG)
	if (mutations != 0)
		elog(LOG, "[GEQO] mutations: %d, generations: %d",
			 mutations, number_generations);
	else
		elog(LOG, "[GEQO] no mutations processed");
#endif

#ifdef GEQO_DEBUG
	print_pool(stdout, pool, 0, pool_size - 1);
#endif

#ifdef GEQO_DEBUG
	elog(DEBUG1, "GEQO best is %.2f after %d generations",
		 pool->data[0].worth, number_generations);
#endif


	/*
	 * got the cheapest query tree processed by geqo; first element of the
	 * population indicates the best query tree
	 */
	best_tour = (Gene *) pool->data[0].string;

	best_rel = gimme_tree(root, best_tour, pool->string_length);

	if (best_rel == NULL)
		elog(ERROR, "geqo failed to make a valid plan");

	/* DBG: show the query plan */
#ifdef NOT_USED
	print_plan(best_plan, root);
#endif

	/* ... free memory stuff */
	free_chromo(root, momma);
	free_chromo(root, daddy);

#if defined (ERX)
	free_edge_table(root, edge_table);
#elif defined(PMX)
	free_chromo(root, kid);
#elif defined(CX)
	free_chromo(root, kid);
	free_city_table(root, city_table);
#elif defined(PX)
	free_chromo(root, kid);
	free_city_table(root, city_table);
#elif defined(OX1)
	free_chromo(root, kid);
	free_city_table(root, city_table);
#elif defined(OX2)
	free_chromo(root, kid);
	free_city_table(root, city_table);
#endif

	free_pool(root, pool);

	/* ... clear root pointer to our private storage */
	root->join_search_private = NULL;

	return best_rel;
}