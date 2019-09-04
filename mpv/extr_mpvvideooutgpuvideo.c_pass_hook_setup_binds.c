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
struct tex_hook {scalar_t__* bind_tex; } ;
struct image {int dummy; } ;
struct gl_video {int num_user_textures; int num_pass_imgs; int /*<<< orphan*/  sc; struct gl_user_shader_tex* user_textures; } ;
struct gl_user_shader_tex {int /*<<< orphan*/  tex; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TRACE (struct gl_video*,char*,char const*,char*) ; 
 int SHADER_MAX_BINDS ; 
 scalar_t__ bstr_equals0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_sc_uniform_texture (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_prelude (struct gl_video*,char const*,int,struct image) ; 
 int pass_bind (struct gl_video*,struct image) ; 
 int /*<<< orphan*/  saved_img_find (struct gl_video*,char*,struct image*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool pass_hook_setup_binds(struct gl_video *p, const char *name,
                                  struct image img, struct tex_hook *hook)
{
    for (int t = 0; t < SHADER_MAX_BINDS; t++) {
        char *bind_name = (char *)hook->bind_tex[t];

        if (!bind_name)
            continue;

        // This is a special name that means "currently hooked texture"
        if (strcmp(bind_name, "HOOKED") == 0) {
            int id = pass_bind(p, img);
            hook_prelude(p, "HOOKED", id, img);
            hook_prelude(p, name, id, img);
            continue;
        }

        // BIND can also be used to load user-defined textures, in which
        // case we will directly load them as a uniform instead of
        // generating the hook_prelude boilerplate
        for (int u = 0; u < p->num_user_textures; u++) {
            struct gl_user_shader_tex *utex = &p->user_textures[u];
            if (bstr_equals0(utex->name, bind_name)) {
                gl_sc_uniform_texture(p->sc, bind_name, utex->tex);
                goto next_bind;
            }
        }

        struct image bind_img;
        if (!saved_img_find(p, bind_name, &bind_img)) {
            // Clean up texture bindings and move on to the next hook
            MP_TRACE(p, "Skipping hook on %s due to no texture named %s.\n",
                     name, bind_name);
            p->num_pass_imgs -= t;
            return false;
        }

        hook_prelude(p, bind_name, pass_bind(p, bind_img), bind_img);

next_bind: ;
    }

    return true;
}