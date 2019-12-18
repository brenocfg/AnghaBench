#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int freespace; scalar_t__ indtuples; scalar_t__ indtuplesSize; } ;
typedef  double Size ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  GISTPageOpaqueData ;
typedef  TYPE_1__ GISTBuildState ;

/* Variables and functions */
 int BLCKSZ ; 
 int SizeOfPageHeaderData ; 
 int pow (double,int) ; 
 scalar_t__ rint (double) ; 

__attribute__((used)) static int
calculatePagesPerBuffer(GISTBuildState *buildstate, int levelStep)
{
	double		pagesPerBuffer;
	double		avgIndexTuplesPerPage;
	double		itupAvgSize;
	Size		pageFreeSpace;

	/* Calc space of index page which is available for index tuples */
	pageFreeSpace = BLCKSZ - SizeOfPageHeaderData - sizeof(GISTPageOpaqueData)
		- sizeof(ItemIdData)
		- buildstate->freespace;

	/*
	 * Calculate average size of already inserted index tuples using gathered
	 * statistics.
	 */
	itupAvgSize = (double) buildstate->indtuplesSize /
		(double) buildstate->indtuples;

	avgIndexTuplesPerPage = pageFreeSpace / itupAvgSize;

	/*
	 * Recalculate required size of buffers.
	 */
	pagesPerBuffer = 2 * pow(avgIndexTuplesPerPage, levelStep);

	return (int) rint(pagesPerBuffer);
}