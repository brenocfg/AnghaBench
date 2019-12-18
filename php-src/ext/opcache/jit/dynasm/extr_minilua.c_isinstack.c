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
struct TYPE_3__ {int /*<<< orphan*/  const* top; int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  const* StkId ;
typedef  TYPE_1__ CallInfo ;

/* Variables and functions */

__attribute__((used)) static int isinstack(CallInfo*ci,const TValue*o){
StkId p;
for(p=ci->base;p<ci->top;p++)
if(o==p)return 1;
return 0;
}