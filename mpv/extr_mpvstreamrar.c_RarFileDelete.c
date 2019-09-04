#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int chunk_count; int /*<<< orphan*/  s; struct TYPE_5__* name; struct TYPE_5__** chunk; struct TYPE_5__* mrl; } ;
typedef  TYPE_1__ rar_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__**) ; 

void RarFileDelete(rar_file_t *file)
{
    for (int i = 0; i < file->chunk_count; i++) {
        free(file->chunk[i]->mrl);
        free(file->chunk[i]);
    }
    talloc_free(file->chunk);
    free(file->name);
    free_stream(file->s);
    free(file);
}