#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int stbi_uc ;
typedef  int stbi__int32 ;
struct TYPE_6__ {int* out; int w; int h; int eflags; int* old_out; int start_x; int start_y; int max_x; int max_y; int line_size; int cur_x; int cur_y; int lflags; int step; int parse; int transparent; int* color_table; int flags; int** pal; void* delay; scalar_t__ lpal; } ;
typedef  TYPE_1__ stbi__gif ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_NOTUSED (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* stbi__errpuc (char*,char*) ; 
 int /*<<< orphan*/  stbi__fill_gif_background (TYPE_1__*,int,int,int,int) ; 
 void* stbi__get16le (int /*<<< orphan*/ *) ; 
 int stbi__get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__gif_header (int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi__gif_parse_colortable (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 scalar_t__ stbi__malloc (int) ; 
 int* stbi__process_gif_raster (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stbi__skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static stbi_uc *stbi__gif_load_next(stbi__context *s, stbi__gif *g, int *comp, int req_comp)
{
   int i;
   stbi_uc *prev_out = 0;

   if (g->out == 0 && !stbi__gif_header(s, g, comp,0))
      return 0; // stbi__g_failure_reason set by stbi__gif_header

   prev_out = g->out;
   g->out = (stbi_uc *) stbi__malloc(4 * g->w * g->h);
   if (g->out == 0) return stbi__errpuc("outofmem", "Out of memory");

   switch ((g->eflags & 0x1C) >> 2) {
      case 0: // unspecified (also always used on 1st frame)
         stbi__fill_gif_background(g, 0, 0, 4 * g->w, 4 * g->w * g->h);
         break;
      case 1: // do not dispose
         if (prev_out) memcpy(g->out, prev_out, 4 * g->w * g->h);
         g->old_out = prev_out;
         break;
      case 2: // dispose to background
         if (prev_out) memcpy(g->out, prev_out, 4 * g->w * g->h);
         stbi__fill_gif_background(g, g->start_x, g->start_y, g->max_x, g->max_y);
         break;
      case 3: // dispose to previous
         if (g->old_out) {
            for (i = g->start_y; i < g->max_y; i += 4 * g->w)
               memcpy(&g->out[i + g->start_x], &g->old_out[i + g->start_x], g->max_x - g->start_x);
         }
         break;
   }

   for (;;) {
      switch (stbi__get8(s)) {
         case 0x2C: /* Image Descriptor */
         {
            int prev_trans = -1;
            stbi__int32 x, y, w, h;
            stbi_uc *o;

            x = stbi__get16le(s);
            y = stbi__get16le(s);
            w = stbi__get16le(s);
            h = stbi__get16le(s);
            if (((x + w) > (g->w)) || ((y + h) > (g->h)))
               return stbi__errpuc("bad Image Descriptor", "Corrupt GIF");

            g->line_size = g->w * 4;
            g->start_x = x * 4;
            g->start_y = y * g->line_size;
            g->max_x   = g->start_x + w * 4;
            g->max_y   = g->start_y + h * g->line_size;
            g->cur_x   = g->start_x;
            g->cur_y   = g->start_y;

            g->lflags = stbi__get8(s);

            if (g->lflags & 0x40) {
               g->step = 8 * g->line_size; // first interlaced spacing
               g->parse = 3;
            } else {
               g->step = g->line_size;
               g->parse = 0;
            }

            if (g->lflags & 0x80) {
               stbi__gif_parse_colortable(s,g->lpal, 2 << (g->lflags & 7), g->eflags & 0x01 ? g->transparent : -1);
               g->color_table = (stbi_uc *) g->lpal;
            } else if (g->flags & 0x80) {
               if (g->transparent >= 0 && (g->eflags & 0x01)) {
                  prev_trans = g->pal[g->transparent][3];
                  g->pal[g->transparent][3] = 0;
               }
               g->color_table = (stbi_uc *) g->pal;
            } else
               return stbi__errpuc("missing color table", "Corrupt GIF");

            o = stbi__process_gif_raster(s, g);
            if (o == NULL) return NULL;

            if (prev_trans != -1)
               g->pal[g->transparent][3] = (stbi_uc) prev_trans;

            return o;
         }

         case 0x21: // Comment Extension.
         {
            int len;
            if (stbi__get8(s) == 0xF9) { // Graphic Control Extension.
               len = stbi__get8(s);
               if (len == 4) {
                  g->eflags = stbi__get8(s);
                  g->delay = stbi__get16le(s);
                  g->transparent = stbi__get8(s);
               } else {
                  stbi__skip(s, len);
                  break;
               }
            }
            while ((len = stbi__get8(s)) != 0)
               stbi__skip(s, len);
            break;
         }

         case 0x3B: // gif stream termination code
            return (stbi_uc *) s; // using '1' causes warning on some compilers

         default:
            return stbi__errpuc("unknown code", "Corrupt GIF");
      }
   }

   STBI_NOTUSED(req_comp);
}