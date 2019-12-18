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
struct TYPE_6__ {TYPE_1__* ls; } ;
struct TYPE_5__ {int /*<<< orphan*/  lastline; } ;
typedef  int /*<<< orphan*/  OpCode ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ABx (int /*<<< orphan*/ ,int,unsigned int) ; 
 int luaK_code (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int luaK_codeABx(FuncState*fs,OpCode o,int a,unsigned int bc){
return luaK_code(fs,CREATE_ABx(o,a,bc),fs->ls->lastline);
}