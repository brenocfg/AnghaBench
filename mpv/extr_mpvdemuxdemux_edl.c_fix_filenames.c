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
struct tl_parts {int num_parts; struct tl_part* parts; } ;
struct tl_part {int /*<<< orphan*/  filename; } ;
struct bstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 char* mp_basename (int /*<<< orphan*/ ) ; 
 struct bstr mp_dirname (char*) ; 
 int /*<<< orphan*/  mp_path_join_bstr (struct tl_parts*,struct bstr,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fix_filenames(struct tl_parts *parts, char *source_path)
{
    struct bstr dirname = mp_dirname(source_path);
    for (int n = 0; n < parts->num_parts; n++) {
        struct tl_part *part = &parts->parts[n];
        char *filename = mp_basename(part->filename); // plain filename only
        part->filename = mp_path_join_bstr(parts, dirname, bstr0(filename));
    }
}