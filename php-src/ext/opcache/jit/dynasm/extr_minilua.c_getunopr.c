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
typedef  int /*<<< orphan*/  UnOpr ;

/* Variables and functions */
 int /*<<< orphan*/  OPR_LEN ; 
 int /*<<< orphan*/  OPR_MINUS ; 
 int /*<<< orphan*/  OPR_NOT ; 
 int /*<<< orphan*/  OPR_NOUNOPR ; 
#define  TK_NOT 128 

__attribute__((used)) static UnOpr getunopr(int op){
switch(op){
case TK_NOT:return OPR_NOT;
case'-':return OPR_MINUS;
case'#':return OPR_LEN;
default:return OPR_NOUNOPR;
}
}