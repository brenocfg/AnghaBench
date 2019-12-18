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
 int /*<<< orphan*/  render_256 ; 
 int /*<<< orphan*/  render_ansi ; 
 int /*<<< orphan*/  render_ascii ; 
 int /*<<< orphan*/  render_greyscale ; 
 int /*<<< orphan*/  render_rgb ; 
 int /*<<< orphan*/  renderer ; 

__attribute__((used)) static void selectrenderer(int mode) {
	switch (mode) {
	case 'a':
		renderer = render_ascii;
		break;
	case 'A':
		renderer = render_ansi;
		break;
	case 'g': renderer = render_greyscale; break;
	case '2': renderer = render_256; break;
	default:
		renderer = render_rgb;
		break;
	}
}