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

/* Variables and functions */
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  uchar (char const) ; 

__attribute__((used)) static const char*scanformat(lua_State*L,const char*strfrmt,char*form){
const char*p=strfrmt;
while(*p!='\0'&&strchr("-+ #0",*p)!=NULL)p++;
if((size_t)(p-strfrmt)>=sizeof("-+ #0"))
luaL_error(L,"invalid format (repeated flags)");
if(isdigit(uchar(*p)))p++;
if(isdigit(uchar(*p)))p++;
if(*p=='.'){
p++;
if(isdigit(uchar(*p)))p++;
if(isdigit(uchar(*p)))p++;
}
if(isdigit(uchar(*p)))
luaL_error(L,"invalid format (width or precision too long)");
*(form++)='%';
strncpy(form,strfrmt,p-strfrmt+1);
form+=p-strfrmt+1;
*form='\0';
return p;
}