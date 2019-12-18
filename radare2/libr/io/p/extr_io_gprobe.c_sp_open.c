#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct termios {int c_cflag; int c_iflag; scalar_t__* c_cc; scalar_t__ c_oflag; scalar_t__ c_lflag; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ WriteTotalTimeoutConstant; scalar_t__ WriteTotalTimeoutMultiplier; scalar_t__ ReadTotalTimeoutConstant; scalar_t__ ReadTotalTimeoutMultiplier; scalar_t__ ReadIntervalTimeout; } ;
struct gport {char* name; scalar_t__ hdl; int /*<<< orphan*/  fd; void* wait_running; void* writing; TYPE_2__ timeouts; } ;
struct TYPE_4__ {int ByteSize; void* fOutX; void* fInX; void* fOutxDsrFlow; int /*<<< orphan*/  fDtrControl; void* fOutxCtsFlow; int /*<<< orphan*/  fRtsControl; int /*<<< orphan*/  StopBits; int /*<<< orphan*/  Parity; int /*<<< orphan*/  BaudRate; void* fAbortOnError; void* fNull; void* fErrorChar; void* fDsrSensitivity; int /*<<< orphan*/  fBinary; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DCB ;
typedef  int /*<<< orphan*/  COMSTAT ;

/* Variables and functions */
 int /*<<< orphan*/  B115200 ; 
 int /*<<< orphan*/  CBR_115200 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSIZE ; 
 int CSTOPB ; 
 scalar_t__ ClearCommError (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTR_CONTROL_DISABLE ; 
 int EV_ERR ; 
 int EV_RXCHAR ; 
 void* FALSE ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_FLAG_OVERLAPPED ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int IGNBRK ; 
 int /*<<< orphan*/  INIT_OVERLAPPED (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  NOPARITY ; 
 int /*<<< orphan*/  ONESTOPBIT ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int O_NOCTTY ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  RTS_CONTROL_DISABLE ; 
 scalar_t__ SetCommMask (scalar_t__,int) ; 
 int /*<<< orphan*/  SetCommState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ SetCommTimeouts (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TRUE ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  r_sandbox_open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_conv_utf8_to_win (char*) ; 
 int /*<<< orphan*/  read_ovl ; 
 int restart_wait (struct gport*) ; 
 int /*<<< orphan*/  sp_close (struct gport*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  wait_ovl ; 
 int /*<<< orphan*/  write_ovl ; 

__attribute__((used)) static int sp_open (struct gport *port) {
#if __WINDOWS__
	int ret;
	DWORD errors;
	char *escaped_port_name;
	COMSTAT status;
	DCB dcb;
	LPTSTR filename_;

	/* Prefix port name with '\\.\' to work with ports above COM9. */
	if (!(escaped_port_name = malloc (strlen (port->name) + 5))) {
		return -1;
	}
	sprintf (escaped_port_name, "\\\\.\\%s", port->name);

	filename_ = r_sys_conv_utf8_to_win (escaped_port_name);

	port->hdl = CreateFile (filename_, GENERIC_READ | GENERIC_WRITE, 0, 0,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	free (escaped_port_name);

	if (port->hdl == INVALID_HANDLE_VALUE) {
		return -1;
	}

	/* All timeouts initially disabled. */
	port->timeouts.ReadIntervalTimeout = 0;
	port->timeouts.ReadTotalTimeoutMultiplier = 0;
	port->timeouts.ReadTotalTimeoutConstant = 0;
	port->timeouts.WriteTotalTimeoutMultiplier = 0;
	port->timeouts.WriteTotalTimeoutConstant = 0;

	if (SetCommTimeouts (port->hdl, &port->timeouts) == 0) {
		sp_close (port);
		return -1;
	}

	/* Prepare OVERLAPPED structures. */
#define INIT_OVERLAPPED(ovl)                                                                             \
	do {                                                                                             \
		memset (&port->ovl, 0, sizeof (port->ovl));                                              \
		port->ovl.hEvent = INVALID_HANDLE_VALUE;                                                 \
		if ((port->ovl.hEvent = CreateEvent (NULL, TRUE, TRUE, NULL)) == INVALID_HANDLE_VALUE) { \
			sp_close (port);                                                                 \
			return -1;                                                                       \
		}                                                                                        \
	} while (0)

	INIT_OVERLAPPED (read_ovl);
	INIT_OVERLAPPED (write_ovl);
	INIT_OVERLAPPED (wait_ovl);

	/* Set event mask for RX and error events. */
	if (SetCommMask (port->hdl, EV_RXCHAR | EV_ERR) == 0) {
		sp_close (port);
		return -1;
	}

	port->writing = FALSE;
	port->wait_running = FALSE;

	ret = restart_wait (port);

	if (ret < 0) {
		sp_close (port);
		return -1;
	}

	dcb.fBinary = TRUE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fAbortOnError = FALSE;

	if (ClearCommError (port->hdl, &errors, &status) == 0) {
		return -1;
	}

	dcb.BaudRate = CBR_115200;

	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fInX = FALSE;
	dcb.fOutX = FALSE;

	if (!SetCommState (port->hdl, &dcb)) {
		return -1;
	}

	return 0;
#else
	struct termios tty = {0};

	if ((port->fd = r_sandbox_open (port->name, O_NONBLOCK | O_NOCTTY | O_RDWR, 0)) < 0) {
		return -1;
	}

	if (tcgetattr (port->fd, &tty) != 0) {
		sp_close (port);
		return -1;
	}

	cfsetospeed (&tty, B115200);
	cfsetispeed (&tty, B115200);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
	tty.c_iflag &= ~IGNBRK;
	tty.c_lflag = 0;
	tty.c_oflag = 0;
	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = 0;
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);

	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~(PARENB | PARODD);
	tty.c_cflag &= ~CSTOPB;
#ifdef CRTSCTS
	tty.c_cflag &= ~CRTSCTS;
#else
	tty.c_cflag &= ~020000000000;
#endif

	if (tcsetattr (port->fd, TCSANOW, &tty) != 0) {
		return -1;
	}

	return 0;
#endif
}