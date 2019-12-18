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
struct spiffs_dirent {size_t type; int size; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  spiffs_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_opendir (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SPIFFS_readdir (int /*<<< orphan*/ *,struct spiffs_dirent*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const,int,char*) ; 

__attribute__((used)) static void list (void)
{
  spiffs_DIR dir;
  if (!SPIFFS_opendir (&fs, "/", &dir))
    die ("spiffs_opendir");
  struct spiffs_dirent de;
  while (SPIFFS_readdir (&dir, &de))
  {
    static const char types[] = "?fdhs"; // file, dir, hardlink, softlink
    char name[sizeof(de.name)+1] = { 0 };
    memcpy (name, de.name, sizeof(de.name));
    printf("%c %6u %s\n", types[de.type], de.size, name);
  }
  SPIFFS_closedir (&dir);
}