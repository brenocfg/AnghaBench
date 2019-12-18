#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* paInfoTypes; scalar_t__ pszCustomTabs; scalar_t__ pszUrlJump2; scalar_t__ pszUrlJump1; scalar_t__ pszJump2; scalar_t__ pszJump1; scalar_t__ pszHome; scalar_t__ pszFile; scalar_t__ pszIndex; scalar_t__ pszToc; scalar_t__ pszCaption; scalar_t__ pszType; } ;
typedef  TYPE_1__ HH_WINTYPEW ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (void*) ; 

__attribute__((used)) static inline void wintype_free(HH_WINTYPEW *wintype)
{
    heap_free((void *)wintype->pszType);
    heap_free((void *)wintype->pszCaption);
    heap_free(wintype->paInfoTypes);
    heap_free((void *)wintype->pszToc);
    heap_free((void *)wintype->pszIndex);
    heap_free((void *)wintype->pszFile);
    heap_free((void *)wintype->pszHome);
    heap_free((void *)wintype->pszJump1);
    heap_free((void *)wintype->pszJump2);
    heap_free((void *)wintype->pszUrlJump1);
    heap_free((void *)wintype->pszUrlJump2);
    heap_free((void *)wintype->pszCustomTabs);
}