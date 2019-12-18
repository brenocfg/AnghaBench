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
 int getjump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  patchtestreg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void removevalues(FuncState*fs,int list){
for(;list!=(-1);list=getjump(fs,list))
patchtestreg(fs,list,((1<<8)-1));
}