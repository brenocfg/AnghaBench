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
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  fixjump (int /*<<< orphan*/ *,int,int) ; 
 int getjump (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void luaK_concat(FuncState*fs,int*l1,int l2){
if(l2==(-1))return;
else if(*l1==(-1))
*l1=l2;
else{
int list=*l1;
int next;
while((next=getjump(fs,list))!=(-1))
list=next;
fixjump(fs,list,l2);
}
}