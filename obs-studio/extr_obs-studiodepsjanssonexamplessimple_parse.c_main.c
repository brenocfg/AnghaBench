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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int MAX_CHARS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_json (char*) ; 
 int /*<<< orphan*/  print_json (int /*<<< orphan*/ *) ; 
 char* read_line (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[]) {
    char line[MAX_CHARS];

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(-1);
    }

    while (read_line(line, MAX_CHARS) != (char *)NULL) {

        /* parse text into JSON structure */
        json_t *root = load_json(line);

        if (root) {
            /* print and release the JSON structure */
            print_json(root);
            json_decref(root);
        }
    }

    return 0;
}