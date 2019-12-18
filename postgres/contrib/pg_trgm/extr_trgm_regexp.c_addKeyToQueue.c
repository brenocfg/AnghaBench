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
typedef  int /*<<< orphan*/  TrgmStateKey ;
struct TYPE_3__ {int /*<<< orphan*/  keysQueue; } ;
typedef  TYPE_1__ TrgmNFA ;

/* Variables and functions */
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
addKeyToQueue(TrgmNFA *trgmNFA, TrgmStateKey *key)
{
	TrgmStateKey *keyCopy = (TrgmStateKey *) palloc(sizeof(TrgmStateKey));

	memcpy(keyCopy, key, sizeof(TrgmStateKey));
	trgmNFA->keysQueue = lappend(trgmNFA->keysQueue, keyCopy);
}