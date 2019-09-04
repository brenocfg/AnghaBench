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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

int is_leon() {
  #define MAXCHAR 1000
  FILE *fp;
  char str[MAXCHAR];
  char* filename = "/proc/cmdline";

  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("Could not open file %s",filename);
    return 0;
  }
  fgets(str, MAXCHAR, fp);
  fclose(fp);
  return strstr(str, "letv") != NULL;
}