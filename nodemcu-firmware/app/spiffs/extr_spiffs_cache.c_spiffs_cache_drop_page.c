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
typedef  int /*<<< orphan*/  spiffs_page_ix ;
struct TYPE_3__ {int /*<<< orphan*/  ix; } ;
typedef  TYPE_1__ spiffs_cache_page ;
typedef  int /*<<< orphan*/  spiffs ;

/* Variables and functions */
 int /*<<< orphan*/  spiffs_cache_page_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* spiffs_cache_page_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spiffs_cache_drop_page(spiffs *fs, spiffs_page_ix pix) {
  spiffs_cache_page *cp =  spiffs_cache_page_get(fs, pix);
  if (cp) {
    spiffs_cache_page_free(fs, cp->ix, 0);
  }
}