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
struct mp_imgfmt_entry {int fmt; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  av_get_pix_fmt (char*) ; 
 scalar_t__ bstr_equals0 (int /*<<< orphan*/ ,scalar_t__) ; 
 char* bstrdup0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mp_imgfmt_entry* mp_imgfmt_list ; 
 int pixfmt2imgfmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

int mp_imgfmt_from_name(bstr name)
{
    int img_fmt = 0;
    for (const struct mp_imgfmt_entry *p = mp_imgfmt_list; p->name; ++p) {
        if (bstr_equals0(name, p->name)) {
            img_fmt = p->fmt;
            break;
        }
    }
    if (!img_fmt) {
        char *t = bstrdup0(NULL, name);
        img_fmt = pixfmt2imgfmt(av_get_pix_fmt(t));
        talloc_free(t);
    }
    return img_fmt;
}