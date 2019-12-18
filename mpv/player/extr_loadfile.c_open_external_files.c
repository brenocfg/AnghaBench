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
struct MPContext {int /*<<< orphan*/  playback_abort; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */
 int /*<<< orphan*/  mp_add_external_file (struct MPContext*,char*,int,int /*<<< orphan*/ ) ; 
 char** mp_dup_str_array (void*,char**) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void open_external_files(struct MPContext *mpctx, char **files,
                                enum stream_type filter)
{
    // Need a copy, because the option value could be mutated during iteration.
    void *tmp = talloc_new(NULL);
    files = mp_dup_str_array(tmp, files);

    for (int n = 0; files && files[n]; n++)
        mp_add_external_file(mpctx, files[n], filter, mpctx->playback_abort);

    talloc_free(tmp);
}