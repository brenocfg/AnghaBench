#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
typedef  double float4 ;
struct TYPE_23__ {int pos; int len; } ;
typedef  TYPE_3__ WordEntry ;
struct TYPE_24__ {int stats_valid; double stanullfrac; double stawidth; double stadistinct; double** stanumbers; int* numnumbers; scalar_t__** stavalues; int* numvalues; int* statyplen; int* statypbyval; char* statypalign; int /*<<< orphan*/ * statypid; int /*<<< orphan*/ * stacoll; int /*<<< orphan*/ * staop; int /*<<< orphan*/ * stakind; int /*<<< orphan*/  anl_context; TYPE_1__* attr; } ;
typedef  TYPE_4__ VacAttrStats ;
struct TYPE_22__ {int /*<<< orphan*/  length; scalar_t__ lexeme; } ;
struct TYPE_25__ {int frequency; int delta; TYPE_2__ key; } ;
typedef  TYPE_5__ TrackItem ;
struct TYPE_28__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  match; int /*<<< orphan*/  hash; } ;
struct TYPE_27__ {char* lexeme; int length; } ;
struct TYPE_26__ {int size; } ;
struct TYPE_21__ {int attstattarget; } ;
typedef  TYPE_6__* TSVector ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_7__ LexemeHashKey ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  TYPE_8__ HASHCTL ;
typedef  scalar_t__ Datum ;
typedef  scalar_t__ (* AnalyzeAttrFetchFunc ) (TYPE_4__*,int,int*) ;

/* Variables and functions */
 TYPE_3__* ARRPTR (TYPE_6__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  DatumGetPointer (scalar_t__) ; 
 TYPE_6__* DatumGetTSVector (scalar_t__) ; 
 int HASH_COMPARE ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int HASH_FUNCTION ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  MemSet (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCELEM ; 
 char* STRPTR (TYPE_6__*) ; 
 int /*<<< orphan*/  TEXTOID ; 
 scalar_t__ TSVectorGetDatum (TYPE_6__*) ; 
 int /*<<< orphan*/  TextEqualOperator ; 
 scalar_t__ VARSIZE_ANY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstring_to_text_with_len (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_8__*,int) ; 
 int hash_get_num_entries (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lexeme_hash ; 
 int /*<<< orphan*/  lexeme_match ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_6__*) ; 
 int /*<<< orphan*/  prune_lexemes_hashtable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qsort (TYPE_5__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trackitem_compare_frequencies_desc ; 
 int /*<<< orphan*/  trackitem_compare_lexemes ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

__attribute__((used)) static void
compute_tsvector_stats(VacAttrStats *stats,
					   AnalyzeAttrFetchFunc fetchfunc,
					   int samplerows,
					   double totalrows)
{
	int			num_mcelem;
	int			null_cnt = 0;
	double		total_width = 0;

	/* This is D from the LC algorithm. */
	HTAB	   *lexemes_tab;
	HASHCTL		hash_ctl;
	HASH_SEQ_STATUS scan_status;

	/* This is the current bucket number from the LC algorithm */
	int			b_current;

	/* This is 'w' from the LC algorithm */
	int			bucket_width;
	int			vector_no,
				lexeme_no;
	LexemeHashKey hash_key;
	TrackItem  *item;

	/*
	 * We want statistics_target * 10 lexemes in the MCELEM array.  This
	 * multiplier is pretty arbitrary, but is meant to reflect the fact that
	 * the number of individual lexeme values tracked in pg_statistic ought to
	 * be more than the number of values for a simple scalar column.
	 */
	num_mcelem = stats->attr->attstattarget * 10;

	/*
	 * We set bucket width equal to (num_mcelem + 10) / 0.007 as per the
	 * comment above.
	 */
	bucket_width = (num_mcelem + 10) * 1000 / 7;

	/*
	 * Create the hashtable. It will be in local memory, so we don't need to
	 * worry about overflowing the initial size. Also we don't need to pay any
	 * attention to locking and memory management.
	 */
	MemSet(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(LexemeHashKey);
	hash_ctl.entrysize = sizeof(TrackItem);
	hash_ctl.hash = lexeme_hash;
	hash_ctl.match = lexeme_match;
	hash_ctl.hcxt = CurrentMemoryContext;
	lexemes_tab = hash_create("Analyzed lexemes table",
							  num_mcelem,
							  &hash_ctl,
							  HASH_ELEM | HASH_FUNCTION | HASH_COMPARE | HASH_CONTEXT);

	/* Initialize counters. */
	b_current = 1;
	lexeme_no = 0;

	/* Loop over the tsvectors. */
	for (vector_no = 0; vector_no < samplerows; vector_no++)
	{
		Datum		value;
		bool		isnull;
		TSVector	vector;
		WordEntry  *curentryptr;
		char	   *lexemesptr;
		int			j;

		vacuum_delay_point();

		value = fetchfunc(stats, vector_no, &isnull);

		/*
		 * Check for null/nonnull.
		 */
		if (isnull)
		{
			null_cnt++;
			continue;
		}

		/*
		 * Add up widths for average-width calculation.  Since it's a
		 * tsvector, we know it's varlena.  As in the regular
		 * compute_minimal_stats function, we use the toasted width for this
		 * calculation.
		 */
		total_width += VARSIZE_ANY(DatumGetPointer(value));

		/*
		 * Now detoast the tsvector if needed.
		 */
		vector = DatumGetTSVector(value);

		/*
		 * We loop through the lexemes in the tsvector and add them to our
		 * tracking hashtable.
		 */
		lexemesptr = STRPTR(vector);
		curentryptr = ARRPTR(vector);
		for (j = 0; j < vector->size; j++)
		{
			bool		found;

			/*
			 * Construct a hash key.  The key points into the (detoasted)
			 * tsvector value at this point, but if a new entry is created, we
			 * make a copy of it.  This way we can free the tsvector value
			 * once we've processed all its lexemes.
			 */
			hash_key.lexeme = lexemesptr + curentryptr->pos;
			hash_key.length = curentryptr->len;

			/* Lookup current lexeme in hashtable, adding it if new */
			item = (TrackItem *) hash_search(lexemes_tab,
											 (const void *) &hash_key,
											 HASH_ENTER, &found);

			if (found)
			{
				/* The lexeme is already on the tracking list */
				item->frequency++;
			}
			else
			{
				/* Initialize new tracking list element */
				item->frequency = 1;
				item->delta = b_current - 1;

				item->key.lexeme = palloc(hash_key.length);
				memcpy(item->key.lexeme, hash_key.lexeme, hash_key.length);
			}

			/* lexeme_no is the number of elements processed (ie N) */
			lexeme_no++;

			/* We prune the D structure after processing each bucket */
			if (lexeme_no % bucket_width == 0)
			{
				prune_lexemes_hashtable(lexemes_tab, b_current);
				b_current++;
			}

			/* Advance to the next WordEntry in the tsvector */
			curentryptr++;
		}

		/* If the vector was toasted, free the detoasted copy. */
		if (TSVectorGetDatum(vector) != value)
			pfree(vector);
	}

	/* We can only compute real stats if we found some non-null values. */
	if (null_cnt < samplerows)
	{
		int			nonnull_cnt = samplerows - null_cnt;
		int			i;
		TrackItem **sort_table;
		int			track_len;
		int			cutoff_freq;
		int			minfreq,
					maxfreq;

		stats->stats_valid = true;
		/* Do the simple null-frac and average width stats */
		stats->stanullfrac = (double) null_cnt / (double) samplerows;
		stats->stawidth = total_width / (double) nonnull_cnt;

		/* Assume it's a unique column (see notes above) */
		stats->stadistinct = -1.0 * (1.0 - stats->stanullfrac);

		/*
		 * Construct an array of the interesting hashtable items, that is,
		 * those meeting the cutoff frequency (s - epsilon)*N.  Also identify
		 * the minimum and maximum frequencies among these items.
		 *
		 * Since epsilon = s/10 and bucket_width = 1/epsilon, the cutoff
		 * frequency is 9*N / bucket_width.
		 */
		cutoff_freq = 9 * lexeme_no / bucket_width;

		i = hash_get_num_entries(lexemes_tab);	/* surely enough space */
		sort_table = (TrackItem **) palloc(sizeof(TrackItem *) * i);

		hash_seq_init(&scan_status, lexemes_tab);
		track_len = 0;
		minfreq = lexeme_no;
		maxfreq = 0;
		while ((item = (TrackItem *) hash_seq_search(&scan_status)) != NULL)
		{
			if (item->frequency > cutoff_freq)
			{
				sort_table[track_len++] = item;
				minfreq = Min(minfreq, item->frequency);
				maxfreq = Max(maxfreq, item->frequency);
			}
		}
		Assert(track_len <= i);

		/* emit some statistics for debug purposes */
		elog(DEBUG3, "tsvector_stats: target # mces = %d, bucket width = %d, "
			 "# lexemes = %d, hashtable size = %d, usable entries = %d",
			 num_mcelem, bucket_width, lexeme_no, i, track_len);

		/*
		 * If we obtained more lexemes than we really want, get rid of those
		 * with least frequencies.  The easiest way is to qsort the array into
		 * descending frequency order and truncate the array.
		 */
		if (num_mcelem < track_len)
		{
			qsort(sort_table, track_len, sizeof(TrackItem *),
				  trackitem_compare_frequencies_desc);
			/* reset minfreq to the smallest frequency we're keeping */
			minfreq = sort_table[num_mcelem - 1]->frequency;
		}
		else
			num_mcelem = track_len;

		/* Generate MCELEM slot entry */
		if (num_mcelem > 0)
		{
			MemoryContext old_context;
			Datum	   *mcelem_values;
			float4	   *mcelem_freqs;

			/*
			 * We want to store statistics sorted on the lexeme value using
			 * first length, then byte-for-byte comparison. The reason for
			 * doing length comparison first is that we don't care about the
			 * ordering so long as it's consistent, and comparing lengths
			 * first gives us a chance to avoid a strncmp() call.
			 *
			 * This is different from what we do with scalar statistics --
			 * they get sorted on frequencies. The rationale is that we
			 * usually search through most common elements looking for a
			 * specific value, so we can grab its frequency.  When values are
			 * presorted we can employ binary search for that.  See
			 * ts_selfuncs.c for a real usage scenario.
			 */
			qsort(sort_table, num_mcelem, sizeof(TrackItem *),
				  trackitem_compare_lexemes);

			/* Must copy the target values into anl_context */
			old_context = MemoryContextSwitchTo(stats->anl_context);

			/*
			 * We sorted statistics on the lexeme value, but we want to be
			 * able to find out the minimal and maximal frequency without
			 * going through all the values.  We keep those two extra
			 * frequencies in two extra cells in mcelem_freqs.
			 *
			 * (Note: the MCELEM statistics slot definition allows for a third
			 * extra number containing the frequency of nulls, but we don't
			 * create that for a tsvector column, since null elements aren't
			 * possible.)
			 */
			mcelem_values = (Datum *) palloc(num_mcelem * sizeof(Datum));
			mcelem_freqs = (float4 *) palloc((num_mcelem + 2) * sizeof(float4));

			/*
			 * See comments above about use of nonnull_cnt as the divisor for
			 * the final frequency estimates.
			 */
			for (i = 0; i < num_mcelem; i++)
			{
				TrackItem  *item = sort_table[i];

				mcelem_values[i] =
					PointerGetDatum(cstring_to_text_with_len(item->key.lexeme,
															 item->key.length));
				mcelem_freqs[i] = (double) item->frequency / (double) nonnull_cnt;
			}
			mcelem_freqs[i++] = (double) minfreq / (double) nonnull_cnt;
			mcelem_freqs[i] = (double) maxfreq / (double) nonnull_cnt;
			MemoryContextSwitchTo(old_context);

			stats->stakind[0] = STATISTIC_KIND_MCELEM;
			stats->staop[0] = TextEqualOperator;
			stats->stacoll[0] = DEFAULT_COLLATION_OID;
			stats->stanumbers[0] = mcelem_freqs;
			/* See above comment about two extra frequency fields */
			stats->numnumbers[0] = num_mcelem + 2;
			stats->stavalues[0] = mcelem_values;
			stats->numvalues[0] = num_mcelem;
			/* We are storing text values */
			stats->statypid[0] = TEXTOID;
			stats->statyplen[0] = -1;	/* typlen, -1 for varlena */
			stats->statypbyval[0] = false;
			stats->statypalign[0] = 'i';
		}
	}
	else
	{
		/* We found only nulls; assume the column is entirely null */
		stats->stats_valid = true;
		stats->stanullfrac = 1.0;
		stats->stawidth = 0;	/* "unknown" */
		stats->stadistinct = 0.0;	/* "unknown" */
	}

	/*
	 * We don't need to bother cleaning up any of our temporary palloc's. The
	 * hashtable should also go away, as it used a child memory context.
	 */
}