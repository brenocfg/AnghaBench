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
struct rawfb_context {int dummy; } ;
struct nk_vec2i {int x; int y; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 int MAX_POINTS ; 
 int /*<<< orphan*/  nk_rawfb_ctx_setpixel (struct rawfb_context const*,int,int,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_fill_polygon(const struct rawfb_context *rawfb,
    const struct nk_vec2i *pnts, int count, const struct nk_color col)
{
    int i = 0;
    #define MAX_POINTS 64
    int left = 10000, top = 10000, bottom = 0, right = 0;
    int nodes, nodeX[MAX_POINTS], pixelX, pixelY, j, swap ;

    if (count == 0) return;
    if (count > MAX_POINTS)
        count = MAX_POINTS;

    /* Get polygon dimensions */
    for (i = 0; i < count; i++) {
        if (left > pnts[i].x)
            left = pnts[i].x;
        if (right < pnts[i].x)
            right = pnts[i].x;
        if (top > pnts[i].y)
            top = pnts[i].y;
        if (bottom < pnts[i].y)
            bottom = pnts[i].y;
    } bottom++; right++;

    /* Polygon scanline algorithm released under public-domain by Darel Rex Finley, 2007 */
    /*  Loop through the rows of the image. */
    for (pixelY = top; pixelY < bottom; pixelY ++) {
        nodes = 0; /*  Build a list of nodes. */
        j = count - 1;
        for (i = 0; i < count; i++) {
            if (((pnts[i].y < pixelY) && (pnts[j].y >= pixelY)) ||
                ((pnts[j].y < pixelY) && (pnts[i].y >= pixelY))) {
                nodeX[nodes++]= (int)((float)pnts[i].x
                     + ((float)pixelY - (float)pnts[i].y) / ((float)pnts[j].y - (float)pnts[i].y)
                     * ((float)pnts[j].x - (float)pnts[i].x));
            } j = i;
        }

        /*  Sort the nodes, via a simple “Bubble” sort. */
        i = 0;
        while (i < nodes - 1) {
            if (nodeX[i] > nodeX[i+1]) {
                swap = nodeX[i];
                nodeX[i] = nodeX[i+1];
                nodeX[i+1] = swap;
                if (i) i--;
            } else i++;
        }
        /*  Fill the pixels between node pairs. */
        for (i = 0; i < nodes; i += 2) {
            if (nodeX[i+0] >= right) break;
            if (nodeX[i+1] > left) {
                if (nodeX[i+0] < left) nodeX[i+0] = left ;
                if (nodeX[i+1] > right) nodeX[i+1] = right;
                for (pixelX = nodeX[i]; pixelX < nodeX[i + 1]; pixelX++)
                    nk_rawfb_ctx_setpixel(rawfb, pixelX, pixelY, col);
            }
        }
    }
    #undef MAX_POINTS
}