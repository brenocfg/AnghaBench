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
struct TYPE_3__ {int /*<<< orphan*/  tf; } ;
typedef  TYPE_1__* PTHEME_CLASS ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  MSSTYLES_CloseThemeFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT MSSTYLES_CloseThemeClass(PTHEME_CLASS tc)
{
    MSSTYLES_CloseThemeFile (tc->tf);
    return S_OK;
}