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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PKSPIN_LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID TcpipInterlockedInsertTailList( PLIST_ENTRY ListHead,
				     PLIST_ENTRY Item,
				     PKSPIN_LOCK Lock ) {
    InsertTailList( ListHead, Item );
}