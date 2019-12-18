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

/* Variables and functions */
 int /*<<< orphan*/  eraseCharCounts () ; 
 int /*<<< orphan*/  eraseKeyCodes () ; 
 int /*<<< orphan*/  eraseTableAbbreviation () ; 
 int relativityActive ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int tempOff ; 

bool deactivateRelativity(void)
{  
  rgblight_mode(9);
  eraseKeyCodes();
  eraseTableAbbreviation();
  eraseCharCounts();
  relativityActive = false;
  tempOff = false;
  return false;
}