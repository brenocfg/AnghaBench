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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int pushresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tofilep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_fclose(lua_State*L){
FILE**p=tofilep(L);
int ok=(fclose(*p)==0);
*p=NULL;
return pushresult(L,ok,NULL);
}