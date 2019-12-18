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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ hue; int /*<<< orphan*/  sat; } ;

/* Variables and functions */
 size_t biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fled_val ; 
 int /*<<< orphan*/ * fleds ; 
 TYPE_1__* layer_colors ; 
 size_t lc_size ; 
 int /*<<< orphan*/  sethsv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t layer_state_set_kb(uint32_t state) {
    // Determine and set colour of layer LED according to current layer
    // if hue = sat = 0, leave LED off
    uint8_t layer = biton32(state);
    
    if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].hue == 0))
        sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    else
        setrgb(0, 0, 0, &fleds[1]);
    
    return state;
}