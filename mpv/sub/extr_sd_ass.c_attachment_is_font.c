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
struct mp_log {int dummy; } ;
struct demux_attachment {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__* font_exts ; 
 scalar_t__* font_mimetypes ; 
 int /*<<< orphan*/  mp_warn (struct mp_log*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool attachment_is_font(struct mp_log *log, struct demux_attachment *f)
{
    if (!f->name || !f->type || !f->data || !f->data_size)
        return false;
    for (int n = 0; font_mimetypes[n]; n++) {
        if (strcmp(font_mimetypes[n], f->type) == 0)
            return true;
    }
    // fallback: match against file extension
    char *ext = strlen(f->name) > 4 ? f->name + strlen(f->name) - 4 : "";
    for (int n = 0; font_exts[n]; n++) {
        if (strcasecmp(ext, font_exts[n]) == 0) {
            mp_warn(log, "Loading font attachment '%s' with MIME type %s. "
                    "Assuming this is a broken Matroska file, which was "
                    "muxed without setting a correct font MIME type.\n",
                    f->name, f->type);
            return true;
        }
    }
    return false;
}