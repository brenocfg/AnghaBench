#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ nk_handle ;
struct TYPE_5__ {int /*<<< orphan*/  font; } ;
typedef  TYPE_2__ NkAllegro5Font ;

/* Variables and functions */
 float al_get_text_width (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static float
nk_allegro5_font_get_text_width(nk_handle handle, float height, const char *text, int len)
{
    NkAllegro5Font *font = (NkAllegro5Font*)handle.ptr;
    if (!font || !text) {
        return 0;
    }
    /* We must copy into a new buffer with exact length null-terminated
       as nuklear uses variable size buffers and al_get_text_width doesn't
       accept a length, it infers length from null-termination
       (which is unsafe API design by allegro devs!) */
    char strcpy[len+1];
    strncpy((char*)&strcpy, text, len);
    strcpy[len] = '\0';
    return al_get_text_width(font->font, strcpy);
}