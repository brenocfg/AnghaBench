#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pxPrevious; int /*<<< orphan*/ * pxNext; int /*<<< orphan*/  xItemValue; } ;
struct TYPE_7__ {scalar_t__ uxNumberOfItems; TYPE_1__ xListEnd; int /*<<< orphan*/ * pxIndex; } ;
typedef  TYPE_2__ List_t ;
typedef  int /*<<< orphan*/  ListItem_t ;

/* Variables and functions */
 int /*<<< orphan*/  listSET_LIST_INTEGRITY_CHECK_1_VALUE (TYPE_2__* const) ; 
 int /*<<< orphan*/  listSET_LIST_INTEGRITY_CHECK_2_VALUE (TYPE_2__* const) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 

void vListInitialise( List_t * const pxList )
{
	/* The list structure contains a list item which is used to mark the
	end of the list.  To initialise the list the list end is inserted
	as the only list entry. */
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );			/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */

	/* The list end value is the highest possible value in the list to
	ensure it remains at the end of the list. */
	pxList->xListEnd.xItemValue = portMAX_DELAY;

	/* The list end next and previous pointers point to itself so we know
	when the list is empty. */
	pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );	/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */

	pxList->uxNumberOfItems = ( UBaseType_t ) 0U;

	/* Write known values into the list if
	configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES is set to 1. */
	listSET_LIST_INTEGRITY_CHECK_1_VALUE( pxList );
	listSET_LIST_INTEGRITY_CHECK_2_VALUE( pxList );
}