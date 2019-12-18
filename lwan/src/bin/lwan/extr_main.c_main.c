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
struct lwan_url_map {char* prefix; int /*<<< orphan*/  member_1; } ;
struct lwan_straitjacket {scalar_t__ user_name; int /*<<< orphan*/  chroot_path; } ;
struct lwan_config {char* listener; char* config_file_path; } ;
struct lwan {int dummy; } ;

/* Variables and functions */
#define  ARGS_FAILED 130 
#define  ARGS_SERVE_FILES 129 
#define  ARGS_USE_CONFIG 128 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SERVE_FILES (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 struct lwan_config* lwan_get_default_config () ; 
 int /*<<< orphan*/  lwan_init (struct lwan*) ; 
 int /*<<< orphan*/  lwan_init_with_config (struct lwan*,struct lwan_config*) ; 
 int /*<<< orphan*/  lwan_main_loop (struct lwan*) ; 
 int /*<<< orphan*/  lwan_set_url_map (struct lwan*,struct lwan_url_map const*) ; 
 int /*<<< orphan*/  lwan_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_status_info (char*,char*) ; 
 int /*<<< orphan*/  lwan_straitjacket_enforce (struct lwan_straitjacket*) ; 
 int parse_args (int,char**,struct lwan_config*,char*,struct lwan_straitjacket*) ; 
 char* strdup (char*) ; 

int
main(int argc, char *argv[])
{
    struct lwan l;
    struct lwan_config c;
    struct lwan_straitjacket sj = {};
    char root_buf[PATH_MAX];
    char *root = root_buf;
    int ret = EXIT_SUCCESS;

    if (!getcwd(root, PATH_MAX))
        return 1;

    c = *lwan_get_default_config();
    c.listener = strdup("*:8080");

    switch (parse_args(argc, argv, &c, root, &sj)) {
    case ARGS_SERVE_FILES:
        lwan_status_info("Serving files from %s", root);

        if (sj.chroot_path) {
            root = "/";
        }
        lwan_straitjacket_enforce(&sj);

        lwan_init_with_config(&l, &c);

        const struct lwan_url_map map[] = {
            { .prefix = "/", SERVE_FILES(root) },
            { }
        };
        lwan_set_url_map(&l, map);
        break;
    case ARGS_USE_CONFIG:
        lwan_straitjacket_enforce(&sj);
        if (c.config_file_path)
            lwan_init_with_config(&l, &c);
        else
            lwan_init(&l);
        break;
    case ARGS_FAILED:
        ret = EXIT_FAILURE;
        goto out;
    }

    lwan_main_loop(&l);
    lwan_shutdown(&l);

out:
    free(c.listener);
    free(c.config_file_path);
    free((char *)sj.user_name);

    return ret;
}