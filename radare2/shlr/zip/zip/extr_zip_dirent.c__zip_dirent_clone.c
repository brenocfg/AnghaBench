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
struct zip_dirent {int cloned; scalar_t__ changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zip_dirent_init (struct zip_dirent*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct zip_dirent*,struct zip_dirent const*,int) ; 

struct zip_dirent *
_zip_dirent_clone(const struct zip_dirent *sde)
{
    struct zip_dirent *tde;

    if ((tde=(struct zip_dirent *)malloc(sizeof(*tde))) == NULL)
	return NULL;

    if (sde)
	memcpy(tde, sde, sizeof(*sde));
    else
	_zip_dirent_init(tde);
    
    tde->changed = 0;
    tde->cloned = 1;

    return tde;
}