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
struct vo {int /*<<< orphan*/  log; int /*<<< orphan*/  global; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  current; TYPE_1__* opts; int /*<<< orphan*/  frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  opts; scalar_t__ outdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct vo*,char*,char*) ; 
 int /*<<< orphan*/  image_writer_file_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 char* mp_path_join (void*,scalar_t__,char*) ; 
 scalar_t__ strlen (scalar_t__) ; 
 char* talloc_asprintf (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (!p->current)
        return;

    (p->frame)++;

    void *t = talloc_new(NULL);
    char *filename = talloc_asprintf(t, "%08d.%s", p->frame,
                                     image_writer_file_ext(p->opts->opts));

    if (p->opts->outdir && strlen(p->opts->outdir))
        filename = mp_path_join(t, p->opts->outdir, filename);

    MP_INFO(vo, "Saving %s\n", filename);
    write_image(p->current, p->opts->opts, filename, vo->global, vo->log);

    talloc_free(t);
    mp_image_unrefp(&p->current);
}