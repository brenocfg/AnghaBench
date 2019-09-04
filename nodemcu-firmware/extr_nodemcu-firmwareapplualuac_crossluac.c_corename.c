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
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 char* getstr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * luaS_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * luaS_newlstr (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static TString *corename(lua_State *L, const TString *filename)
{
 const char *fn = getstr(filename)+1;
 const char *s = strrchr(fn, '/');
 if (!s) s = strrchr(fn, '\\');
 s = s ? s + 1 : fn;
 while (*s == '.') s++;
 const char *e = strchr(s, '.');
 int l = e ? e - s: strlen(s);
 return l ? luaS_newlstr (L, s, l) : luaS_new(L, fn);
}