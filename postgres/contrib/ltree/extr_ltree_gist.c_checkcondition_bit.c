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
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ ITEM ;

/* Variables and functions */
 scalar_t__ FLG_CANLOOKSIGN (int /*<<< orphan*/ ) ; 
 int GETBIT (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
checkcondition_bit(void *checkval, ITEM *val)
{
	return (FLG_CANLOOKSIGN(val->flag)) ? GETBIT(checkval, HASHVAL(val->val)) : true;
}