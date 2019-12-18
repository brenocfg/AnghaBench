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
struct nk_text_edit {int dummy; } ;
typedef  int /*<<< orphan*/  nk_handle ;

/* Variables and functions */
 char* SDL_GetClipboardText () ; 
 int /*<<< orphan*/  nk_strlen (char const*) ; 
 int /*<<< orphan*/  nk_textedit_paste (struct nk_text_edit*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_sdl_clipboard_paste(nk_handle usr, struct nk_text_edit *edit)
{
    const char *text = SDL_GetClipboardText();
    if (text) nk_textedit_paste(edit, text, nk_strlen(text));
    (void)usr;
}