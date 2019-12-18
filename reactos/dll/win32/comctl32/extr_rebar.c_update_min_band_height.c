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
struct TYPE_4__ {scalar_t__ cyChild; scalar_t__ hwndChild; int /*<<< orphan*/  cyHeader; int /*<<< orphan*/  cyMinBand; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  TYPE_1__ REBAR_BAND ;

/* Variables and functions */
 scalar_t__ REBARSPACE (TYPE_1__*) ; 
 scalar_t__ REBAR_NO_CHILD_HEIGHT ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void update_min_band_height(const REBAR_INFO *infoPtr, REBAR_BAND *lpBand)
{
    lpBand->cyMinBand = max(lpBand->cyHeader,
        (lpBand->hwndChild ? lpBand->cyChild + REBARSPACE(lpBand) : REBAR_NO_CHILD_HEIGHT));
}