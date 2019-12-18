#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {char const* buff; int /*<<< orphan*/  f; scalar_t__ extraline; } ;
typedef  TYPE_1__ LoadF ;

/* Variables and functions */
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 size_t fread (char const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*getF(lua_State*L,void*ud,size_t*size){
LoadF*lf=(LoadF*)ud;
(void)L;
if(lf->extraline){
lf->extraline=0;
*size=1;
return"\n";
}
if(feof(lf->f))return NULL;
*size=fread(lf->buff,1,sizeof(lf->buff),lf->f);
return(*size>0)?lf->buff:NULL;
}