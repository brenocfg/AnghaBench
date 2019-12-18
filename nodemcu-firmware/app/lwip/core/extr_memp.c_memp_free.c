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
typedef  int /*<<< orphan*/  u8_t ;
struct memp {struct memp* next; } ;
typedef  size_t memp_t ;
typedef  int mem_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int /*<<< orphan*/ * MEMP_SIZE ; 
 int /*<<< orphan*/  MEMP_STATS_DEC (int /*<<< orphan*/ ,size_t) ; 
 int MEM_ALIGNMENT ; 
 int /*<<< orphan*/  SYS_ARCH_DECL_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_UNPROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memp_overflow_check_all () ; 
 int /*<<< orphan*/  memp_overflow_check_element_overflow (struct memp*,size_t) ; 
 int /*<<< orphan*/  memp_overflow_check_element_underflow (struct memp*,size_t) ; 
 int memp_sanity () ; 
 struct memp** memp_tab ; 
 int /*<<< orphan*/  old_level ; 
 int /*<<< orphan*/  used ; 

void
memp_free(memp_t type, void *mem)
{
  struct memp *memp;
  SYS_ARCH_DECL_PROTECT(old_level);

  if (mem == NULL) {
    return;
  }
  LWIP_ASSERT("memp_free: mem properly aligned",
                ((mem_ptr_t)mem % MEM_ALIGNMENT) == 0);

  memp = (struct memp *)(void *)((u8_t*)mem - MEMP_SIZE);

  SYS_ARCH_PROTECT(old_level);
#if MEMP_OVERFLOW_CHECK
#if MEMP_OVERFLOW_CHECK >= 2
  memp_overflow_check_all();
#else
  memp_overflow_check_element_overflow(memp, type);
  memp_overflow_check_element_underflow(memp, type);
#endif /* MEMP_OVERFLOW_CHECK >= 2 */
#endif /* MEMP_OVERFLOW_CHECK */

  MEMP_STATS_DEC(used, type);

  memp->next = memp_tab[type];
  memp_tab[type] = memp;

#if MEMP_SANITY_CHECK
  LWIP_ASSERT("memp sanity", memp_sanity());
#endif /* MEMP_SANITY_CHECK */

  SYS_ARCH_UNPROTECT(old_level);
}