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
struct mp_imgfmt_entry {int fmt; char* name; } ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 char MP_SELECT_LE_BE (char,char) ; 
 TYPE_1__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgfmt2pixfmt (int) ; 
 struct mp_imgfmt_entry* mp_imgfmt_list ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 int strlen (char*) ; 

char *mp_imgfmt_to_name_buf(char *buf, size_t buf_size, int fmt)
{
    const char *name = NULL;
    const struct mp_imgfmt_entry *p = mp_imgfmt_list;
    for (; p->fmt; p++) {
        if (p->name && p->fmt == fmt) {
            name = p->name;
            break;
        }
    }
    if (!name) {
        const AVPixFmtDescriptor *pixdesc = av_pix_fmt_desc_get(imgfmt2pixfmt(fmt));
        if (pixdesc)
            name = pixdesc->name;
    }
    if (!name)
        name = "unknown";
    snprintf(buf, buf_size, "%s", name);
    int len = strlen(buf);
    if (len > 2 && buf[len - 2] == MP_SELECT_LE_BE('l', 'b') && buf[len - 1] == 'e')
        buf[len - 2] = '\0';
    return buf;
}