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
struct mg_str {int len; char* p; } ;
struct mg_connection {int /*<<< orphan*/ * user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_slfs_set_new_file_size (char*,intptr_t) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static struct mg_str upload_fname(struct mg_connection *nc,
                                  struct mg_str fname) {
  struct mg_str lfn;
  char *fn = malloc(fname.len + 4);
  memcpy(fn, "SL:", 3);
  memcpy(fn + 3, fname.p, fname.len);
  fn[3 + fname.len] = '\0';
  if (nc->user_data != NULL) {
    intptr_t cl = (intptr_t) nc->user_data;
    if (cl >= 0) {
      fs_slfs_set_new_file_size(fn + 3, cl);
    }
  }
  lfn.len = fname.len + 4;
  lfn.p = fn;
  return lfn;
}