#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_6__ {int breaklist; struct TYPE_6__* previous; scalar_t__ upval; int /*<<< orphan*/  nactvar; int /*<<< orphan*/  isbreakable; } ;
struct TYPE_5__ {TYPE_2__* bl; int /*<<< orphan*/  nactvar; } ;
typedef  TYPE_1__ FuncState ;
typedef  TYPE_2__ BlockCnt ;

/* Variables and functions */

__attribute__((used)) static void enterblock(FuncState*fs,BlockCnt*bl,lu_byte isbreakable){
bl->breaklist=(-1);
bl->isbreakable=isbreakable;
bl->nactvar=fs->nactvar;
bl->upval=0;
bl->previous=fs->bl;
fs->bl=bl;
}