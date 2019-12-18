#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int StrategyNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  SimilarityStrategyNumber 130 
#define  StrictWordSimilarityStrategyNumber 129 
#define  WordSimilarityStrategyNumber 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 double similarity_threshold ; 
 double strict_word_similarity_threshold ; 
 double word_similarity_threshold ; 

double
index_strategy_get_limit(StrategyNumber strategy)
{
	switch (strategy)
	{
		case SimilarityStrategyNumber:
			return similarity_threshold;
		case WordSimilarityStrategyNumber:
			return word_similarity_threshold;
		case StrictWordSimilarityStrategyNumber:
			return strict_word_similarity_threshold;
		default:
			elog(ERROR, "unrecognized strategy number: %d", strategy);
			break;
	}

	return 0.0;					/* keep compiler quiet */
}