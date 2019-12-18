#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct afs_volume {scalar_t__ name_len; int type; TYPE_1__* cell; int /*<<< orphan*/  servers_lock; int /*<<< orphan*/  flags; scalar_t__ update_at; scalar_t__ servers_seq; struct afs_vldb_entry* servers; int /*<<< orphan*/  name; int /*<<< orphan*/  vid; } ;
struct afs_vldb_entry {scalar_t__ name_len; scalar_t__ seq; int /*<<< orphan*/  name; } ;
struct afs_server_list {scalar_t__ name_len; scalar_t__ seq; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_MAXVOLNAME ; 
 int /*<<< orphan*/  AFS_VOLUME_NEEDS_UPDATE ; 
 scalar_t__ IS_ERR (struct afs_vldb_entry*) ; 
 int PTR_ERR (struct afs_vldb_entry*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct afs_vldb_entry* afs_alloc_server_list (TYPE_1__*,struct key*,struct afs_vldb_entry*,int) ; 
 scalar_t__ afs_annotate_server_list (struct afs_vldb_entry*,struct afs_vldb_entry*) ; 
 int /*<<< orphan*/  afs_put_serverlist (int /*<<< orphan*/ ,struct afs_vldb_entry*) ; 
 struct afs_vldb_entry* afs_vl_lookup_vldb (TYPE_1__*,struct key*,char*,int) ; 
 scalar_t__ afs_volume_record_life ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct afs_vldb_entry*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_update_volume_status(struct afs_volume *volume, struct key *key)
{
	struct afs_server_list *new, *old, *discard;
	struct afs_vldb_entry *vldb;
	char idbuf[16];
	int ret, idsz;

	_enter("");

	/* We look up an ID by passing it as a decimal string in the
	 * operation's name parameter.
	 */
	idsz = sprintf(idbuf, "%llu", volume->vid);

	vldb = afs_vl_lookup_vldb(volume->cell, key, idbuf, idsz);
	if (IS_ERR(vldb)) {
		ret = PTR_ERR(vldb);
		goto error;
	}

	/* See if the volume got renamed. */
	if (vldb->name_len != volume->name_len ||
	    memcmp(vldb->name, volume->name, vldb->name_len) != 0) {
		/* TODO: Use RCU'd string. */
		memcpy(volume->name, vldb->name, AFS_MAXVOLNAME);
		volume->name_len = vldb->name_len;
	}

	/* See if the volume's server list got updated. */
	new = afs_alloc_server_list(volume->cell, key,
				    vldb, (1 << volume->type));
	if (IS_ERR(new)) {
		ret = PTR_ERR(new);
		goto error_vldb;
	}

	write_lock(&volume->servers_lock);

	discard = new;
	old = volume->servers;
	if (afs_annotate_server_list(new, old)) {
		new->seq = volume->servers_seq + 1;
		volume->servers = new;
		smp_wmb();
		volume->servers_seq++;
		discard = old;
	}

	volume->update_at = ktime_get_real_seconds() + afs_volume_record_life;
	clear_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags);
	write_unlock(&volume->servers_lock);
	ret = 0;

	afs_put_serverlist(volume->cell->net, discard);
error_vldb:
	kfree(vldb);
error:
	_leave(" = %d", ret);
	return ret;
}