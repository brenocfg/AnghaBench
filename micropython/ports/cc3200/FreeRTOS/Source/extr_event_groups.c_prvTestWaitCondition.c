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
typedef  int const EventBits_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ const pdFALSE ; 
 scalar_t__ pdTRUE ; 

__attribute__((used)) static BaseType_t prvTestWaitCondition( const EventBits_t uxCurrentEventBits, const EventBits_t uxBitsToWaitFor, const BaseType_t xWaitForAllBits )
{
BaseType_t xWaitConditionMet = pdFALSE;

	if( xWaitForAllBits == pdFALSE )
	{
		/* Task only has to wait for one bit within uxBitsToWaitFor to be
		set.  Is one already set? */
		if( ( uxCurrentEventBits & uxBitsToWaitFor ) != ( EventBits_t ) 0 )
		{
			xWaitConditionMet = pdTRUE;
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	else
	{
		/* Task has to wait for all the bits in uxBitsToWaitFor to be set.
		Are they set already? */
		if( ( uxCurrentEventBits & uxBitsToWaitFor ) == uxBitsToWaitFor )
		{
			xWaitConditionMet = pdTRUE;
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}

	return xWaitConditionMet;
}