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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ws2801_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ws2801_color(uint8_t r, uint8_t g, uint8_t b) {
    ws2801_byte(r);
    ws2801_byte(g);
    ws2801_byte(b);
}