#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  L; int /*<<< orphan*/  Z; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  LoadBlock (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  LoadVar (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * luaS_newlstr (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  luaZ_direct_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ luaZ_get_crt_address (int /*<<< orphan*/ ) ; 
 char* luaZ_openspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static TString* LoadString(LoadState* S)
{
 int32_t size;
 LoadVar(S,size);
 if (size==0)
  return NULL;
 else
 {
  char* s;
  if (!luaZ_direct_mode(S->Z)) {
   s = luaZ_openspace(S->L,S->b,size);
   LoadBlock(S,s,size);
   return luaS_newlstr(S->L,s,size-1); /* remove trailing zero */
  } else {
   s = (char*)luaZ_get_crt_address(S->Z);
   LoadBlock(S,NULL,size);
   return luaS_newlstr(S->L,s,size-1);
  }
 }
}