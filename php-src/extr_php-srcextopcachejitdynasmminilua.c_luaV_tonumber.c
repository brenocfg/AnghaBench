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
typedef  int /*<<< orphan*/  const TValue ;

/* Variables and functions */
 scalar_t__ luaO_str2d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const TValue*luaV_tonumber(const TValue*obj,TValue*n){
lua_Number num;
if(ttisnumber(obj))return obj;
if(ttisstring(obj)&&luaO_str2d(svalue(obj),&num)){
setnvalue(n,num);
return n;
}
else
return NULL;
}