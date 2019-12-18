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
struct lwan_config {char* listener; } ;
typedef  int /*<<< orphan*/  path_buf ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_current_dir_name () ; 
 char* lwan_get_config_path (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_help(const char *argv0, const struct lwan_config *config)
{
    char path_buf[PATH_MAX];
    char *current_dir = get_current_dir_name();
    const char *config_file = lwan_get_config_path(path_buf, sizeof(path_buf));

    printf("Usage: %s [--root /path/to/root/dir] [--listen addr:port]\n", argv0);
    printf("\t[--config] [--user username] [--chroot] [--modules|--handlers]\n");
    printf("Serve files through HTTP.\n\n");
    printf("Options:\n");
    printf("\t-r, --root      Path to serve files from (default: ./wwwroot).\n");
    printf("\t-l, --listen    Listener (default: %s).\n", config->listener);
    printf("\t-c, --config    Path to config file path.\n");
    printf("\t-u, --user      Username to drop privileges to (root required).\n");
    printf("\t-C, --chroot    Chroot to path passed to --root (root required).\n");
    printf("\t-m, --modules   Print information about available modules.\n");
    printf("\t-H, --handlers  Print information about available handlers.\n");
    printf("\t-h, --help      This.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  Serve system-wide documentation:\n");
    printf("        %s -r /usr/share/doc\n", argv0);
    printf("  Serve on a different port:\n");
    printf("        %s -l '*:1337'\n", argv0);
    printf("  Use %s from %s:\n", config_file, current_dir);
    printf("        %s\n", argv0);
    printf("  Use /etc/%s:\n", config_file);
    printf("        %s -c /etc/%s\n", argv0, config_file);
    printf("\n");
    printf("Report bugs at <https://github.com/lpereira/lwan>.\n");

    free(current_dir);
}