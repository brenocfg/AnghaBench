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
struct TYPE_2__ {int egcmode; scalar_t__ memlimit; } ;

/* Variables and functions */
 int EGC_ALWAYS ; 
 int EGC_ON_ALLOC_FAILURE ; 
 int EGC_ON_MEM_LIMIT ; 
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ l_check_memlimit (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  luaC_fullgc (int /*<<< orphan*/ *) ; 
 scalar_t__ system_get_free_heap_size () ; 
 scalar_t__ this_realloc (void*,size_t,size_t) ; 

__attribute__((used)) static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
  lua_State *L = (lua_State *)ud;
  int mode = L == NULL ? 0 : G(L)->egcmode;
  void *nptr;

  if (nsize == 0) {
#ifdef DEBUG_ALLOCATOR
    return (void *)this_realloc(ptr, osize, nsize);
#else
    free(ptr);
    return NULL;
#endif
  }
  if (L != NULL && (mode & EGC_ALWAYS)) /* always collect memory if requested */
    luaC_fullgc(L);
#ifndef LUA_CROSS_COMPILER
  if (L != NULL && (mode & EGC_ON_MEM_LIMIT) && G(L)->memlimit < 0 &&
      (system_get_free_heap_size() < (-G(L)->memlimit)))
    luaC_fullgc(L);
#endif
  if(nsize > osize && L != NULL) {
#if defined(LUA_STRESS_EMERGENCY_GC)
    luaC_fullgc(L);
#endif
    if(G(L)->memlimit > 0 && (mode & EGC_ON_MEM_LIMIT) && l_check_memlimit(L, nsize - osize))
      return NULL;
  }
  nptr = (void *)this_realloc(ptr, osize, nsize);
  if (nptr == NULL && L != NULL && (mode & EGC_ON_ALLOC_FAILURE)) {
    luaC_fullgc(L); /* emergency full collection. */
    nptr = (void *)this_realloc(ptr, osize, nsize); /* try allocation again */
  }
  return nptr;
}