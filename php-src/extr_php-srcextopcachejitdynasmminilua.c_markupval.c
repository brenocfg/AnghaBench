#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nactvar; int upval; struct TYPE_5__* previous; } ;
struct TYPE_4__ {TYPE_2__* bl; } ;
typedef  TYPE_1__ FuncState ;
typedef  TYPE_2__ BlockCnt ;

/* Variables and functions */

__attribute__((used)) static void markupval(FuncState*fs,int level){
BlockCnt*bl=fs->bl;
while(bl&&bl->nactvar>level)bl=bl->previous;
if(bl)bl->upval=1;
}