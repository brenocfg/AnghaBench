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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  cast_num (int) ; 
 int /*<<< orphan*/  lua_number2int (int,int /*<<< orphan*/ ) ; 
 scalar_t__ luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int arrayindex(const TValue*key){
if(ttisnumber(key)){
lua_Number n=nvalue(key);
int k;
lua_number2int(k,n);
if(luai_numeq(cast_num(k),n))
return k;
}
return-1;
}