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
struct lwan_serve_files_settings {size_t read_ahead; int /*<<< orphan*/  auto_index_readme; int /*<<< orphan*/  directory_list_template; int /*<<< orphan*/  auto_index; int /*<<< orphan*/  serve_precompressed_files; int /*<<< orphan*/  index_html; int /*<<< orphan*/  root_path; } ;
struct hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERVE_FILES_READ_AHEAD_BYTES ; 
 int /*<<< orphan*/  hash_find (struct hash const*,char*) ; 
 int /*<<< orphan*/  parse_bool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_long (char*,int /*<<< orphan*/ ) ; 
 void* serve_files_create (char const*,struct lwan_serve_files_settings*) ; 

__attribute__((used)) static void *serve_files_create_from_hash(const char *prefix,
                                          const struct hash *hash)
{
    struct lwan_serve_files_settings settings = {
        .root_path = hash_find(hash, "path"),
        .index_html = hash_find(hash, "index_path"),
        .serve_precompressed_files =
            parse_bool(hash_find(hash, "serve_precompressed_files"), true),
        .auto_index = parse_bool(hash_find(hash, "auto_index"), true),
        .directory_list_template = hash_find(hash, "directory_list_template"),
        .read_ahead =
            (size_t)parse_long("read_ahead", SERVE_FILES_READ_AHEAD_BYTES),
        .auto_index_readme =
            parse_bool(hash_find(hash, "auto_index_readme"), true),
    };

    return serve_files_create(prefix, &settings);
}