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
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int gdImageAlpha (int /*<<< orphan*/ ,int) ; 
 int gdImageBlue (int /*<<< orphan*/ ,int) ; 
 int gdImageGreen (int /*<<< orphan*/ ,int) ; 
 int gdImageRed (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gdColorMatch(gdImagePtr im, int col1, int col2, float threshold)
{
	const int dr = gdImageRed(im, col1) - gdImageRed(im, col2);
	const int dg = gdImageGreen(im, col1) - gdImageGreen(im, col2);
	const int db = gdImageBlue(im, col1) - gdImageBlue(im, col2);
	const int da = gdImageAlpha(im, col1) - gdImageAlpha(im, col2);
	const int dist = dr * dr + dg * dg + db * db + da * da;

	return (100.0 * dist / 195075) < threshold;
}