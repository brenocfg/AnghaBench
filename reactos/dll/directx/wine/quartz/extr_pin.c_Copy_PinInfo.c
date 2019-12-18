#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pFilter; int /*<<< orphan*/  dir; int /*<<< orphan*/  achName; } ;
typedef  TYPE_1__ PIN_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Copy_PinInfo(PIN_INFO * pDest, const PIN_INFO * pSrc)
{
    /* Tempting to just do a memcpy, but the name field is
       128 characters long! We will probably never exceed 10
       most of the time, so we are better off copying 
       each field manually */
    strcpyW(pDest->achName, pSrc->achName);
    pDest->dir = pSrc->dir;
    pDest->pFilter = pSrc->pFilter;
}