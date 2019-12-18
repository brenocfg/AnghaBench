#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key {int /*<<< orphan*/  description; } ;
struct afs_cell {struct key* anonymous_key; TYPE_1__* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int /*<<< orphan*/ ) ; 
 struct key* key_get (struct key*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  key_type_rxrpc ; 
 struct key* request_key_net (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct key *afs_request_key(struct afs_cell *cell)
{
	struct key *key;

	_enter("{%x}", key_serial(cell->anonymous_key));

	_debug("key %s", cell->anonymous_key->description);
	key = request_key_net(&key_type_rxrpc, cell->anonymous_key->description,
			      cell->net->net, NULL);
	if (IS_ERR(key)) {
		if (PTR_ERR(key) != -ENOKEY) {
			_leave(" = %ld", PTR_ERR(key));
			return key;
		}

		/* act as anonymous user */
		_leave(" = {%x} [anon]", key_serial(cell->anonymous_key));
		return key_get(cell->anonymous_key);
	} else {
		/* act as authorised user */
		_leave(" = {%x} [auth]", key_serial(key));
		return key;
	}
}