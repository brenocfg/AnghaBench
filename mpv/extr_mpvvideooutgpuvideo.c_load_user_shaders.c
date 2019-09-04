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
struct gl_video {int /*<<< orphan*/  ra; int /*<<< orphan*/  log; } ;
struct bstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hook ; 
 int /*<<< orphan*/  add_user_tex ; 
 struct bstr load_cached_file (struct gl_video*,char*) ; 
 int /*<<< orphan*/  parse_user_shader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bstr,struct gl_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_user_shaders(struct gl_video *p, char **shaders)
{
    if (!shaders)
        return;

    for (int n = 0; shaders[n] != NULL; n++) {
        struct bstr file = load_cached_file(p, shaders[n]);
        parse_user_shader(p->log, p->ra, file, p, add_user_hook, add_user_tex);
    }
}