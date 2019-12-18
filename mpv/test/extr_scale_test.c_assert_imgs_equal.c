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
struct scale_test {int fail; } ;
struct TYPE_2__ {int flags; int* bytes; } ;
struct mp_image {scalar_t__ imgfmt; scalar_t__ w; scalar_t__ h; int num_planes; int* stride; TYPE_1__ fmt; void** planes; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MP_IMGFLAG_BYTE_ALIGNED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dump_image (struct scale_test*,char*,struct mp_image*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ memcmp (void*,void*,size_t) ; 
 char* mp_tprintf (int,char*,int) ; 

__attribute__((used)) static void assert_imgs_equal(struct scale_test *stest, FILE *f,
                              struct mp_image *ref, struct mp_image *new)
{
    assert(ref->imgfmt == new->imgfmt);
    assert(ref->w == new->w);
    assert(ref->h == new->h);

    assert(ref->fmt.flags & MP_IMGFLAG_BYTE_ALIGNED);
    assert(ref->fmt.bytes[0]);

    for (int p = 0; p < ref->num_planes; p++) {
        for (int y = 0; y < ref->h; y++) {
            void *line_r = ref->planes[p] + ref->stride[p] * (ptrdiff_t)y;
            void *line_o = new->planes[p] + new->stride[p] * (ptrdiff_t)y;
            size_t size = ref->fmt.bytes[p] * (size_t)new->w;

            bool ok = memcmp(line_r, line_o, size) == 0;
            if (!ok) {
                stest->fail += 1;
                char *fn_a = mp_tprintf(80, "img%d_ref", stest->fail);
                char *fn_b = mp_tprintf(80, "img%d_new", stest->fail);
                fprintf(f, "Images mismatching, dumping to %s/%s\n", fn_a, fn_b);
                dump_image(stest, fn_a, ref);
                dump_image(stest, fn_b, new);
                return;
            }
        }
    }
}