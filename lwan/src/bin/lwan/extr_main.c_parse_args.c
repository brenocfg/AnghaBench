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
struct option {char* name; int has_arg; char val; } ;
struct lwan_straitjacket {char const* user_name; char* chroot_path; } ;
struct lwan_config {char* config_file_path; char* listener; } ;
typedef  enum args { ____Placeholder_args } args ;

/* Variables and functions */
 int ARGS_FAILED ; 
 int ARGS_SERVE_FILES ; 
 int ARGS_USE_CONFIG ; 
 size_t PATH_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt_long (int,char**,char*,struct option const*,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_handler_info () ; 
 int /*<<< orphan*/  print_help (char*,struct lwan_config*) ; 
 int /*<<< orphan*/  print_module_info () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum args
parse_args(int argc, char *argv[], struct lwan_config *config, char *root,
    struct lwan_straitjacket *sj)
{
    static const struct option opts[] = {
        { .name = "root", .has_arg = 1, .val = 'r' },
        { .name = "listen", .has_arg = 1, .val = 'l' },
        { .name = "help", .val = 'h' },
        { .name = "config", .has_arg = 1, .val = 'c' },
        { .name = "chroot", .val = 'C' },
        { .name = "user", .val = 'u', .has_arg = 1 },
        { .name = "modules", .val = 'm' },
        { .name = "handlers", .val = 'H' },
        { }
    };
    int c, optidx = 0;
    enum args result = ARGS_USE_CONFIG;

    while ((c = getopt_long(argc, argv, "Hmhr:l:c:u:C", opts, &optidx)) != -1) {
        switch (c) {
        case 'H':
            print_handler_info();
            return ARGS_FAILED;

        case 'm':
            print_module_info();
            return ARGS_FAILED;

        case 'u':
            free((char *)sj->user_name);
            sj->user_name = (const char *)strdup(optarg);
            break;

        case 'C':
            sj->chroot_path = root;
            break;

        case 'c':
            free(config->config_file_path);
            config->config_file_path = strdup(optarg);
            result = ARGS_USE_CONFIG;
            break;

        case 'l':
            free(config->listener);
            config->listener = strdup(optarg);
            result = ARGS_SERVE_FILES;
            break;

        case 'r': {
            size_t len = strlen(optarg);

            if (len >= PATH_MAX) {
                fprintf(stderr, "Root path length exeeds %d characters\n", PATH_MAX);
                return ARGS_FAILED;
            }

            memcpy(root, optarg, len + 1);
            result = ARGS_SERVE_FILES;
            break;
        }

        case 'h':
            print_help(argv[0], config);
            return ARGS_FAILED;

        default:
            printf("Run %s --help for usage information.\n", argv[0]);
            return ARGS_FAILED;
        }
    }

    return result;
}