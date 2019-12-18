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
struct stream_lang_req {scalar_t__ type; int id; scalar_t__* name; } ;
struct stream {int dummy; } ;
struct sh_stream {scalar_t__ type; int demuxer_id; int /*<<< orphan*/  lang; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CTRL_GET_LANG ; 
 scalar_t__ STREAM_SUB ; 
 int /*<<< orphan*/  stream_control (struct stream*,int /*<<< orphan*/ ,struct stream_lang_req*) ; 
 int /*<<< orphan*/  talloc_strdup (struct sh_stream*,scalar_t__*) ; 

__attribute__((used)) static void get_disc_lang(struct stream *stream, struct sh_stream *sh, bool dvd)
{
    struct stream_lang_req req = {.type = sh->type, .id = sh->demuxer_id};
    if (dvd && sh->type == STREAM_SUB)
        req.id = req.id & 0x1F; // mpeg ID to index
    stream_control(stream, STREAM_CTRL_GET_LANG, &req);
    if (req.name[0])
        sh->lang = talloc_strdup(sh, req.name);
}