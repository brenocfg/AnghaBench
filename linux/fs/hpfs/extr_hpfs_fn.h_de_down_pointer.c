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
struct hpfs_dirent {int /*<<< orphan*/  length; int /*<<< orphan*/  down; } ;
typedef  int /*<<< orphan*/  dnode_secno ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHKCOND (int /*<<< orphan*/ ,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dnode_secno de_down_pointer (struct hpfs_dirent *de)
{
  CHKCOND(de->down,("HPFS: de_down_pointer: !de->down\n"));
  return le32_to_cpu(*(__le32 *) ((void *) de + le16_to_cpu(de->length) - 4));
}